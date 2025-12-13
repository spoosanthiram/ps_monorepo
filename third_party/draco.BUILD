genrule(
    name = "generate_features_h",
    outs = ["src/draco/draco_features.h"],
    cmd = "echo '#pragma once\n\n#define DRACO_POINT_CLOUD_COMPRESSION_SUPPORTED\n'" +
          "'#define DRACO_MESH_COMPRESSION_SUPPORTED\n#define DRACO_NORMAL_ENCODING_SUPPORTED\n'" +
          "'#define DRACO_STANDARD_EDGEBREAKER_SUPPORTED\n#define DRACO_PREDICTIVE_EDGEBREAKER_SUPPORTED\n'" +
          "'#define DRACO_ATTRIBUTE_VALUES_DEDUPLICATION_SUPPORTED' > $@",
)

cc_library(
    name = "draco",
    srcs = [
        # attributes
        "src/draco/attributes/attribute_octahedron_transform.cc",
        "src/draco/attributes/attribute_quantization_transform.cc",
        "src/draco/attributes/attribute_transform.cc",
        "src/draco/attributes/geometry_attribute.cc",
        "src/draco/attributes/point_attribute.cc",

        # compression attributes dec
        "src/draco/compression/attributes/attributes_decoder.cc",
        "src/draco/compression/attributes/kd_tree_attributes_decoder.cc",
        "src/draco/compression/attributes/sequential_attribute_decoder.cc",
        "src/draco/compression/attributes/sequential_attribute_decoders_controller.cc",
        "src/draco/compression/attributes/sequential_integer_attribute_decoder.cc",
        "src/draco/compression/attributes/sequential_normal_attribute_decoder.cc",
        "src/draco/compression/attributes/sequential_quantization_attribute_decoder.cc",

        # compression attributes enc
        "src/draco/compression/attributes/attributes_encoder.cc",
        "src/draco/compression/attributes/kd_tree_attributes_encoder.cc",
        "src/draco/compression/attributes/sequential_attribute_encoder.cc",
        "src/draco/compression/attributes/sequential_attribute_encoders_controller.cc",
        "src/draco/compression/attributes/sequential_integer_attribute_encoder.cc",
        "src/draco/compression/attributes/sequential_normal_attribute_encoder.cc",
        "src/draco/compression/attributes/sequential_quantization_attribute_encoder.cc",

        # compression attributes pred schemes enc
        "src/draco/compression/attributes/prediction_schemes/prediction_scheme_encoder_factory.cc",

        # compression bit coders
        "src/draco/compression/bit_coders/adaptive_rans_bit_decoder.cc",
        "src/draco/compression/bit_coders/adaptive_rans_bit_encoder.cc",
        "src/draco/compression/bit_coders/direct_bit_decoder.cc",
        "src/draco/compression/bit_coders/direct_bit_encoder.cc",
        "src/draco/compression/bit_coders/rans_bit_decoder.cc",
        "src/draco/compression/bit_coders/rans_bit_encoder.cc",
        "src/draco/compression/bit_coders/symbol_bit_decoder.cc",
        "src/draco/compression/bit_coders/symbol_bit_encoder.cc",

        # compression options
        "src/draco/compression/draco_compression_options.cc",

        # compression decode
        "src/draco/compression/decode.cc",

        # compression encode
        "src/draco/compression/encode.cc",
        "src/draco/compression/expert_encode.cc",

        # compression mesh dec
        "src/draco/compression/mesh/mesh_decoder.cc",
        "src/draco/compression/mesh/mesh_edgebreaker_decoder.cc",
        "src/draco/compression/mesh/mesh_edgebreaker_decoder_impl.cc",
        "src/draco/compression/mesh/mesh_sequential_decoder.cc",

        # compression mesh enc
        "src/draco/compression/mesh/mesh_edgebreaker_encoder.cc",
        "src/draco/compression/mesh/mesh_edgebreaker_encoder_impl.cc",
        "src/draco/compression/mesh/mesh_encoder.cc",
        "src/draco/compression/mesh/mesh_sequential_encoder.cc",

        # compression point cloud dec
        "src/draco/compression/point_cloud/point_cloud_decoder.cc",
        "src/draco/compression/point_cloud/point_cloud_kd_tree_decoder.cc",
        "src/draco/compression/point_cloud/point_cloud_sequential_decoder.cc",

        # compression point cloud enc
        "src/draco/compression/point_cloud/point_cloud_encoder.cc",
        "src/draco/compression/point_cloud/point_cloud_kd_tree_encoder.cc",
        "src/draco/compression/point_cloud/point_cloud_sequential_encoder.cc",

        # compression entropy
        "src/draco/compression/entropy/shannon_entropy.cc",
        "src/draco/compression/entropy/symbol_decoding.cc",
        "src/draco/compression/entropy/symbol_encoding.cc",

        # core
        "src/draco/core/bit_utils.cc",
        "src/draco/core/bounding_box.cc",
        "src/draco/core/cycle_timer.cc",
        "src/draco/core/data_buffer.cc",
        "src/draco/core/decoder_buffer.cc",
        "src/draco/core/divide.cc",
        "src/draco/core/draco_types.cc",
        "src/draco/core/encoder_buffer.cc",
        "src/draco/core/hash_utils.cc",
        "src/draco/core/options.cc",
        "src/draco/core/quantization_utils.cc",

        # mesh
        "src/draco/mesh/corner_table.cc",
        "src/draco/mesh/mesh.cc",
        "src/draco/mesh/mesh_are_equivalent.cc",
        "src/draco/mesh/mesh_attribute_corner_table.cc",
        "src/draco/mesh/mesh_cleanup.cc",
        "src/draco/mesh/mesh_features.cc",
        "src/draco/mesh/mesh_misc_functions.cc",
        "src/draco/mesh/mesh_stripifier.cc",
        "src/draco/mesh/triangle_soup_mesh_builder.cc",

        #point cloud
        "src/draco/point_cloud/point_cloud.cc",
        "src/draco/point_cloud/point_cloud_builder.cc",

        # points dec
        "src/draco/compression/point_cloud/algorithms/dynamic_integer_points_kd_tree_decoder.cc",
        "src/draco/compression/point_cloud/algorithms/float_points_tree_decoder.cc",

        # points enc
        "src/draco/compression/point_cloud/algorithms/dynamic_integer_points_kd_tree_encoder.cc",
        "src/draco/compression/point_cloud/algorithms/float_points_tree_encoder.cc",

        # metadata
        "src/draco/metadata/geometry_metadata.cc",
        "src/draco/metadata/metadata.cc",
        "src/draco/metadata/property_attribute.cc",
        "src/draco/metadata/property_table.cc",
        "src/draco/metadata/structural_metadata.cc",
        "src/draco/metadata/structural_metadata_schema.cc",

        # metadata enc
        "src/draco/metadata/metadata_encoder.cc",

        # metadata dec
        "src/draco/metadata/metadata_decoder.cc",
    ],
    hdrs = [
        #generated
        "src/draco/draco_features.h",

        #attributes
        "src/draco/attributes/attribute_octahedron_transform.h",
        "src/draco/attributes/attribute_quantization_transform.h",
        "src/draco/attributes/attribute_transform.h",
        "src/draco/attributes/attribute_transform_data.h",
        "src/draco/attributes/attribute_transform_type.h",
        "src/draco/attributes/geometry_attribute.h",
        "src/draco/attributes/geometry_indices.h",
        "src/draco/attributes/point_attribute.h",

        # compression attributes dec
        "src/draco/compression/attributes/attributes_decoder.h",
        "src/draco/compression/attributes/attributes_decoder_interface.h",
        "src/draco/compression/attributes/kd_tree_attributes_decoder.h",
        "src/draco/compression/attributes/kd_tree_attributes_shared.h",
        "src/draco/compression/attributes/mesh_attribute_indices_encoding_data.h",
        "src/draco/compression/attributes/normal_compression_utils.h",
        "src/draco/compression/attributes/point_d_vector.h",
        "src/draco/compression/attributes/sequential_attribute_decoder.h",
        "src/draco/compression/attributes/sequential_attribute_decoders_controller.h",
        "src/draco/compression/attributes/sequential_integer_attribute_decoder.h",
        "src/draco/compression/attributes/sequential_normal_attribute_decoder.h",
        "src/draco/compression/attributes/sequential_quantization_attribute_decoder.h",

        # compression attributes enc
        "src/draco/compression/attributes/attributes_encoder.h",
        "src/draco/compression/attributes/kd_tree_attributes_encoder.h",
        "src/draco/compression/attributes/linear_sequencer.h",
        "src/draco/compression/attributes/points_sequencer.h",
        "src/draco/compression/attributes/sequential_attribute_encoder.h",
        "src/draco/compression/attributes/sequential_attribute_encoders_controller.h",
        "src/draco/compression/attributes/sequential_integer_attribute_encoder.h",
        "src/draco/compression/attributes/sequential_normal_attribute_encoder.h",
        "src/draco/compression/attributes/sequential_quantization_attribute_encoder.h",

        # compression attributes pred schemes dec
        "src/draco/compression/attributes/prediction_schemes/mesh_prediction_scheme_constrained_multi_parallelogram_decoder.h",
        "src/draco/compression/attributes/prediction_schemes/mesh_prediction_scheme_constrained_multi_parallelogram_shared.h",
        "src/draco/compression/attributes/prediction_schemes/mesh_prediction_scheme_data.h",
        "src/draco/compression/attributes/prediction_schemes/mesh_prediction_scheme_decoder.h",
        "src/draco/compression/attributes/prediction_schemes/mesh_prediction_scheme_geometric_normal_decoder.h",
        "src/draco/compression/attributes/prediction_schemes/mesh_prediction_scheme_geometric_normal_predictor_area.h",
        "src/draco/compression/attributes/prediction_schemes/mesh_prediction_scheme_geometric_normal_predictor_base.h",
        "src/draco/compression/attributes/prediction_schemes/mesh_prediction_scheme_multi_parallelogram_decoder.h",
        "src/draco/compression/attributes/prediction_schemes/mesh_prediction_scheme_parallelogram_decoder.h",
        "src/draco/compression/attributes/prediction_schemes/mesh_prediction_scheme_parallelogram_shared.h",
        "src/draco/compression/attributes/prediction_schemes/mesh_prediction_scheme_tex_coords_decoder.h",
        "src/draco/compression/attributes/prediction_schemes/mesh_prediction_scheme_tex_coords_portable_decoder.h",
        "src/draco/compression/attributes/prediction_schemes/mesh_prediction_scheme_tex_coords_portable_predictor.h",
        "src/draco/compression/attributes/prediction_schemes/prediction_scheme_decoder.h",
        "src/draco/compression/attributes/prediction_schemes/prediction_scheme_decoder_factory.h",
        "src/draco/compression/attributes/prediction_schemes/prediction_scheme_decoder_interface.h",
        "src/draco/compression/attributes/prediction_schemes/prediction_scheme_decoding_transform.h",
        "src/draco/compression/attributes/prediction_schemes/prediction_scheme_delta_decoder.h",
        "src/draco/compression/attributes/prediction_schemes/prediction_scheme_factory.h",
        "src/draco/compression/attributes/prediction_schemes/prediction_scheme_interface.h",
        "src/draco/compression/attributes/prediction_schemes/prediction_scheme_normal_octahedron_canonicalized_decoding_transform.h",
        "src/draco/compression/attributes/prediction_schemes/prediction_scheme_normal_octahedron_canonicalized_transform_base.h",
        "src/draco/compression/attributes/prediction_schemes/prediction_scheme_normal_octahedron_decoding_transform.h",
        "src/draco/compression/attributes/prediction_schemes/prediction_scheme_normal_octahedron_transform_base.h",
        "src/draco/compression/attributes/prediction_schemes/prediction_scheme_wrap_decoding_transform.h",
        "src/draco/compression/attributes/prediction_schemes/prediction_scheme_wrap_transform_base.h",

        # compression attributes pred schemes enc
        "src/draco/compression/attributes/prediction_schemes/mesh_prediction_scheme_constrained_multi_parallelogram_encoder.h",
        "src/draco/compression/attributes/prediction_schemes/mesh_prediction_scheme_encoder.h",
        "src/draco/compression/attributes/prediction_schemes/mesh_prediction_scheme_geometric_normal_encoder.h",
        "src/draco/compression/attributes/prediction_schemes/mesh_prediction_scheme_multi_parallelogram_encoder.h",
        "src/draco/compression/attributes/prediction_schemes/mesh_prediction_scheme_parallelogram_encoder.h",
        "src/draco/compression/attributes/prediction_schemes/mesh_prediction_scheme_tex_coords_encoder.h",
        "src/draco/compression/attributes/prediction_schemes/mesh_prediction_scheme_tex_coords_portable_encoder.h",
        "src/draco/compression/attributes/prediction_schemes/prediction_scheme_delta_encoder.h",
        "src/draco/compression/attributes/prediction_schemes/prediction_scheme_encoder.h",
        "src/draco/compression/attributes/prediction_schemes/prediction_scheme_encoder_factory.h",
        "src/draco/compression/attributes/prediction_schemes/prediction_scheme_encoder_interface.h",
        "src/draco/compression/attributes/prediction_schemes/prediction_scheme_encoding_transform.h",
        "src/draco/compression/attributes/prediction_schemes/prediction_scheme_normal_octahedron_canonicalized_encoding_transform.h",
        "src/draco/compression/attributes/prediction_schemes/prediction_scheme_normal_octahedron_encoding_transform.h",
        "src/draco/compression/attributes/prediction_schemes/prediction_scheme_wrap_encoding_transform.h",

        # compression bit coders
        "src/draco/compression/bit_coders/adaptive_rans_bit_coding_shared.h",
        "src/draco/compression/bit_coders/adaptive_rans_bit_decoder.h",
        "src/draco/compression/bit_coders/adaptive_rans_bit_encoder.h",
        "src/draco/compression/bit_coders/direct_bit_decoder.h",
        "src/draco/compression/bit_coders/direct_bit_encoder.h",
        "src/draco/compression/bit_coders/folded_integer_bit_decoder.h",
        "src/draco/compression/bit_coders/folded_integer_bit_encoder.h",
        "src/draco/compression/bit_coders/rans_bit_decoder.h",
        "src/draco/compression/bit_coders/rans_bit_encoder.h",
        "src/draco/compression/bit_coders/symbol_bit_decoder.h",
        "src/draco/compression/bit_coders/symbol_bit_encoder.h",

        # enc config
        "src/draco/compression/config/compression_shared.h",
        "src/draco/compression/config/draco_options.h",
        "src/draco/compression/config/encoder_options.h",
        "src/draco/compression/config/encoding_features.h",

        # dec config
        "src/draco/compression/config/decoder_options.h",

        # compression options
        "src/draco/compression/draco_compression_options.h",

        # compression decode
        "src/draco/compression/decode.h",

        # compression encode
        "src/draco/compression/encode.h",
        "src/draco/compression/encode_base.h",
        "src/draco/compression/expert_encode.h",

        # compression mesh traverser
        "src/draco/compression/mesh/traverser/depth_first_traverser.h",
        "src/draco/compression/mesh/traverser/max_prediction_degree_traverser.h",
        "src/draco/compression/mesh/traverser/mesh_attribute_indices_encoding_observer.h",
        "src/draco/compression/mesh/traverser/mesh_traversal_sequencer.h",
        "src/draco/compression/mesh/traverser/traverser_base.h",

        # compression mesh dec
        "src/draco/compression/mesh/mesh_decoder.h",
        "src/draco/compression/mesh/mesh_edgebreaker_decoder.h",
        "src/draco/compression/mesh/mesh_edgebreaker_decoder_impl.h",
        "src/draco/compression/mesh/mesh_edgebreaker_decoder_impl_interface.h",
        "src/draco/compression/mesh/mesh_edgebreaker_shared.h",
        "src/draco/compression/mesh/mesh_edgebreaker_traversal_decoder.h",
        "src/draco/compression/mesh/mesh_edgebreaker_traversal_predictive_decoder.h",
        "src/draco/compression/mesh/mesh_edgebreaker_traversal_valence_decoder.h",
        "src/draco/compression/mesh/mesh_sequential_decoder.h",

        # compression mesh enc
        "src/draco/compression/mesh/mesh_edgebreaker_encoder.h",
        "src/draco/compression/mesh/mesh_edgebreaker_encoder_impl.h",
        "src/draco/compression/mesh/mesh_edgebreaker_encoder_impl_interface.h",
        "src/draco/compression/mesh/mesh_edgebreaker_traversal_encoder.h",
        "src/draco/compression/mesh/mesh_edgebreaker_traversal_predictive_encoder.h",
        "src/draco/compression/mesh/mesh_edgebreaker_traversal_valence_encoder.h",
        "src/draco/compression/mesh/mesh_encoder.h",
        "src/draco/compression/mesh/mesh_sequential_encoder.h",

        # compression point cloud dec
        "src/draco/compression/point_cloud/point_cloud_decoder.h",
        "src/draco/compression/point_cloud/point_cloud_kd_tree_decoder.h",
        "src/draco/compression/point_cloud/point_cloud_sequential_decoder.h",

        # compression point cloud enc
        "src/draco/compression/point_cloud/point_cloud_encoder.h",
        "src/draco/compression/point_cloud/point_cloud_kd_tree_encoder.h",
        "src/draco/compression/point_cloud/point_cloud_sequential_encoder.h",

        # compression entropy
        "src/draco/compression/entropy/ans.h",
        "src/draco/compression/entropy/rans_symbol_coding.h",
        "src/draco/compression/entropy/rans_symbol_decoder.h",
        "src/draco/compression/entropy/rans_symbol_encoder.h",
        "src/draco/compression/entropy/shannon_entropy.h",
        "src/draco/compression/entropy/symbol_decoding.h",
        "src/draco/compression/entropy/symbol_encoding.h",

        #core
        "src/draco/core/bit_utils.h",
        "src/draco/core/bounding_box.h",
        "src/draco/core/constants.h",
        "src/draco/core/cycle_timer.h",
        "src/draco/core/data_buffer.h",
        "src/draco/core/decoder_buffer.h",
        "src/draco/core/divide.h",
        "src/draco/core/draco_index_type.h",
        "src/draco/core/draco_index_type_vector.h",
        "src/draco/core/draco_types.h",
        "src/draco/core/draco_version.h",
        "src/draco/core/encoder_buffer.h",
        "src/draco/core/hash_utils.h",
        "src/draco/core/macros.h",
        "src/draco/core/math_utils.h",
        "src/draco/core/options.h",
        "src/draco/core/quantization_utils.h",
        "src/draco/core/status.h",
        "src/draco/core/status_or.h",
        "src/draco/core/varint_decoding.h",
        "src/draco/core/varint_encoding.h",
        "src/draco/core/vector_d.h",

        # mesh
        "src/draco/mesh/corner_table.h",
        "src/draco/mesh/corner_table_iterators.h",
        "src/draco/mesh/mesh.h",
        "src/draco/mesh/mesh_are_equivalent.h",
        "src/draco/mesh/mesh_attribute_corner_table.h",
        "src/draco/mesh/mesh_cleanup.h",
        "src/draco/mesh/mesh_features.h",
        "src/draco/mesh/mesh_indices.h",
        "src/draco/mesh/mesh_misc_functions.h",
        "src/draco/mesh/mesh_stripifier.h",
        "src/draco/mesh/triangle_soup_mesh_builder.h",
        "src/draco/mesh/valence_cache.h",

        #point cloud
        "src/draco/point_cloud/point_cloud.h",
        "src/draco/point_cloud/point_cloud_builder.h",

        # points common
        "src/draco/compression/point_cloud/algorithms/point_cloud_compression_method.h",
        "src/draco/compression/point_cloud/algorithms/point_cloud_types.h",
        "src/draco/compression/point_cloud/algorithms/quantize_points_3.h",
        "src/draco/compression/point_cloud/algorithms/queuing_policy.h",

        # points dec
        "src/draco/compression/point_cloud/algorithms/dynamic_integer_points_kd_tree_decoder.h",
        "src/draco/compression/point_cloud/algorithms/float_points_tree_decoder.h",

        # points enc
        "src/draco/compression/point_cloud/algorithms/dynamic_integer_points_kd_tree_encoder.h",
        "src/draco/compression/point_cloud/algorithms/float_points_tree_encoder.h",

        # metadata
        "src/draco/metadata/geometry_metadata.h",
        "src/draco/metadata/metadata.h",
        "src/draco/metadata/property_attribute.h",
        "src/draco/metadata/property_table.h",
        "src/draco/metadata/structural_metadata.h",
        "src/draco/metadata/structural_metadata_schema.h",

        # metadata enc
        "src/draco/metadata/metadata_encoder.h",

        # metadata dec
        "src/draco/metadata/metadata_decoder.h",

        # texture
        "src/draco/texture/texture_utils.h",
    ],
    includes = ["src"],
    visibility = ["//visibility:public"],
)
